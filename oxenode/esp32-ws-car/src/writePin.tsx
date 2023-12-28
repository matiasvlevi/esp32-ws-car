import { ContentProps, TriggerProps, port } from "@oxenode/core";
import { NumberInput, Select } from "@oxenode/ui";

export const Name = "Write Pin";

export default function Content({ node }: ContentProps) {
    return <>
        <h3>Write Pin</h3>
        <span className="xsmall">Write digital state to pins</span>

        <NumberInput
            nodeId={node.id}
            name='gpioPin'
            value='12'
        />

        <Select
            nodeId={node.id}
            name='mode'
            value='1'
        >
            <option value="1">HIGH</option>
            <option value="0">LOW</option>
        </Select>

        { node.State.err && <>
            <span style={{ margin: '0.25rem', color: 'var(--red)'}}>
                {node.State.err}
            </span>
        </> }
    </>;
}

export function Trigger({ node, controller, inputs: { socket }, state: { mode, gpioPin } }: TriggerProps) {

    const commandBuffer = new Uint8Array([
        0x80,        // GPIO Write
        gpioPin,     // GPIO Pin
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