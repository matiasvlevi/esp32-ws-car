import { ContentProps, TriggerProps, port, useNodeState } from "@oxenode/core";
import { ErrorMessage, NumberInput } from "@oxenode/ui";

export const Name = "Motor Left Right";

export default function Content({ node }: ContentProps) {

    const [left,  setLeft]  = useNodeState(node.id, 'left', 50);
    const [right, setRight] = useNodeState(node.id, 'right', 50);

    return <>
        <h3>Motors</h3>
        <div style={{
            display: 'flex',
            flexDirection: 'row',
            gap: '0.75em',
            padding: '0.5em'
        }}>
            <div>
                <span className="small">Left: </span>

                <NumberInput
                    value={left}
                    onChange={e => setLeft(e.target.value)}
                />
            </div>
            <div>
                <span className="small">Right: </span>

                <NumberInput
                    value={right}
                    onChange={e => setRight(e.target.value)}
                />
            </div>
        </div>

        <ErrorMessage nodeId={node.id}/>
    </>;
}

export async function Trigger({ node, controller, inputs: { socket }, state: { right, left } }: TriggerProps) {

    const motor_right = Math.max(-100, Math.min(right, 100));
    const motor_left = Math.max(-100, Math.min(left, 100));

    const commandBuffer = new Uint8Array([
        0xC0,        // Motor Control
        motor_right,
        motor_left
    ]);
    
    if (socket) {
        socket.send(commandBuffer);
        
        if (node.State.err) delete node.State.err;
    } else {
        node.State.err = 
            `Socket is not connected...`;

        controller.update(node);

        return controller.trigger(0);
    }

    const response = await (new Promise(r => {
        socket.onmessage = (data: string) => r(data);
    }));

    // TODO: handle the response from the device
    console.log(response);

    return controller.trigger(0);
} 

export const ports = [
    port.input().type('trigger'),
    port.input().type('data').label('socket'),
    port.output().type('trigger'),
]