import { onFetchProps, port } from "@oxenode/core";

export const Name = "LED";

export default function Content() {
    return <>
        <h2>LED</h2>
    </>;
}

export const ports = [
    port.input().type('boolean').label('isOn'),
    port.output().type('string').label('command')
        .onFetch(({ inputs: { isOn } }: onFetchProps) => 
         `80 ${+(!isOn)} 00`
        ),
]