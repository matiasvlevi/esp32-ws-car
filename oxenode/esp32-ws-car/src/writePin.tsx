import { ContentProps, TriggerProps, port, useNodeState } from "@oxenode/core";
import { ErrorMessage, NumberInput, Select } from "@oxenode/ui";

export const Name = "Write Pin";

export default function Content({ node }: ContentProps) {
    const [mode, setMode] = useNodeState(node.id, 'mode', 1);
    const [pin, setPin] = useNodeState(node.id, 'pin', 12);
    
    return <>
        <h3>Write Pin</h3>
        <span className="xsmall">Write digital state to pins</span>

        <NumberInput
            value={pin}
            onChange={e => setPin(e.target.value)}
        />

        <Select
            value={mode}
            onChange={e => setMode(e.target.value)}
        >
            <option value="1">HIGH</option>
            <option value="0">LOW</option>
        </Select>

        <ErrorMessage nodeId={node.id}/>
    </>;
}

export function Trigger({ node, controller, inputs: { socket }, state: { mode, pin } }: TriggerProps) {

    const commandBuffer = new Uint8Array([
        0x80,        // GPIO Write
        pin,     // GPIO Pin
        +mode & 1    // state
    ]);

    if (socket) socket.send(commandBuffer);
    else {
        node.State.err = 
            `Socket is not connected...`;

        controller.update(node);

        return controller.trigger(0);
    }

    const promise = new Promise(r => {
        socket.onmessage = (data: string) => {
            r(data);
        };
    });

    controller.setCache('data', promise);

    return controller.trigger(0);
} 

export const ports = [
    port.input().type('trigger'),
    port.input().type('data').label('socket'),
    port.output().type('trigger'),
]