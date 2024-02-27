import { ContentProps, TriggerProps, port, useNodeState } from "@oxenode/core";
import { ErrorMessage, NumberInput, Select } from "@oxenode/ui";

export const Name = "Pin Mode";

export default function Content({ node }: ContentProps) {
    const [mode, setMode] = useNodeState(node.id, 'mode', 1);
    const [pin, setPin]   = useNodeState(node.id, 'pin', 12);

    return <>
        <h3>Pin Mode</h3>
        <span className="xsmall">Write digital state to pins</span>

        <NumberInput
            value={pin}
            onChange={e => setPin(e.target.value)}
        />  

        <Select
            value={mode}
            onChange={e => setMode(e.target.value)}
        >
            {/* 
                Modes are according to the esp32 idf spec 
            
                https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html#_CPPv411gpio_mode_t
            */}
            <option value={(0)}>Disable</option>
            <option value={(1 << 0)}>Input</option>
            <option value={(1 << 1)}>Output</option>
            <option value={(1 << 1) | (1 << 2)}>Output OD</option>
            <option value={(1 << 0) | (1 << 1) | (1 << 2)}>Input Output OD</option>
            <option value={(1 << 0) | (1 << 1)}>Input Output</option>
        </Select>

        <ErrorMessage nodeId={node.id}/>
    </>;
}

export function Trigger({ node, controller, inputs: { socket }, state: { mode, pin } }: TriggerProps) {

    const commandBuffer = new Uint8Array([
        0x7F,        // GPIO Control
        pin,         // GPIO Pin
        +mode & 0x07 // Forward
    ]);

    if (socket) socket.send(commandBuffer);
    else {
        node.State.err = 
            `Socket is not connected...`;
        controller.update(node);

        return controller.trigger(0);
    }

    return controller.trigger(0);
} 

export const ports = [
    port.input().type('trigger'),
    port.input().type('data').label('socket'),
    port.output().type('trigger'),
]