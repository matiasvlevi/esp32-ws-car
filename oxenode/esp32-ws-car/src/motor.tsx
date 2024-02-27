import { ContentProps, TriggerProps, port, useNodeState } from "@oxenode/core";
import { ErrorMessage, NumberInput, Select } from "@oxenode/ui";

export const Name = "Motor";

export default function Content({ node }: ContentProps) {

    const [mode, setMode] = useNodeState(node.id, 'mode', 1);
    const [speed, setSpeed] = useNodeState(node.id, 'speed', 50);

    return <>
        <h3>Motor</h3>
        <span className="xsmall">Control motors</span>

        <Select
            value={mode}
            onChange={e => setMode(e.target.value)}
        >
            <option value="FORWARD">Forward</option>
            <option value="LEFT">Turn Left</option>
            <option value="RIGHT">Turn Right</option>
            <option value="REVERSE">Reverse</option>
            <option value="BRAKE">Brake</option>
        </Select>

        <NumberInput
            value={speed}
            onChange={e => setSpeed(e.target.value)}
        />

        <ErrorMessage nodeId={node.id}/>
    </>;
}

export async function Trigger({ node, controller, inputs: { socket }, state: { mode, speed } }: TriggerProps) {

    let motor_right, motor_left;
    switch(mode) {
        case 'FORWARD':{
            motor_right = new Uint8Array([ speed ]);
            motor_left = new Uint8Array([ speed ]);
            break;
        }
        case 'LEFT':{
            motor_right = new Uint8Array([ speed ]);
            motor_left = new Uint8Array([ speed/5 ]);
            break;
        }
        case 'RIGHT':{
            motor_right = new Uint8Array([ speed/5 ]);
            motor_left = new Uint8Array([ speed ]);
            break;
        }
        case 'REVERSE':{
            motor_right = new Uint8Array([ -speed ]);
            motor_left = new Uint8Array([ -speed ]);
            break;
        }
        case 'BRAKE':{
            motor_right = new Uint8Array([ 0 ]);
            motor_left = new Uint8Array([ 0 ]);
            break;
        }
    }

    const commandBuffer = new Uint8Array([
        0xC0,        // Motor Control
        ...motor_right,
        ...motor_left
    ]);

    console.log(commandBuffer);
    
    if (socket) socket.send(commandBuffer);
    else {
        node.State.err = 
            `Socket is not connected...`;

        controller.update(node);

        return controller.trigger(0);
    }

    const response = await (new Promise(r => {
        socket.onmessage = (data: string) => {
            r(data);
        };
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