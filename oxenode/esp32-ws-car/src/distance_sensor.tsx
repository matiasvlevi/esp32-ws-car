import { ContentProps, TriggerProps, port } from "@oxenode/core";

export const Name = "Distance Sensor";

export default function Content({ node }: ContentProps) {
    return <>
        <h3>Distance (cm)</h3>
        <span>Poor performance! </span>
        { node.State.err && <>
            <span style={{ margin: '0.25rem', color: 'var(--red)'}}>
                {node.State.err}
            </span>
        </> }
    </>;
}

export const ports = [
    port.input().type('data').label('socket'),
    port.output().type('number').label('cm').onFetch(async ({ inputs: { socket }, node }) => {
        const commandBuffer = new Uint8Array([
            0xD0,
            0x00,
            0x00
        ]);
        
        if (socket) socket.send(commandBuffer);
        else {
            node.State.err = 
                `Socket is not connected...`;
        }
    
        const response: any = await (new Promise(r => {
            socket.onmessage = (data: string) => {
                r(data);
            };
        }));
    
        // TODO: handle the response from the device
        console.log(response);

        const data = new Int8Array(await response.data.arrayBuffer());

        console.log(data, (
            (data[1] << 8) |
            data[0]
        ))

        const value =             
            (data[1] << 8) |
            data[0];
        
        return         Math.max(Math.min(60, 
            value < -1  ? 60 : value
        ), 0);; 
    }),
]