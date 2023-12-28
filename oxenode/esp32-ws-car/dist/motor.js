var r={d:(e,n)=>{for(var t in n)r.o(n,t)&&!r.o(e,t)&&Object.defineProperty(e,t,{enumerable:!0,get:n[t]})},o:(r,e)=>Object.prototype.hasOwnProperty.call(r,e)},e={};r.d(e,{VG:()=>c,xz:()=>u,ZP:()=>l,Tt:()=>p});const n=window.OxenodeCore,t=window.OxenodeUi,o=window.jsxRuntimeExports;function a(r){return function(r){if(Array.isArray(r))return i(r)}(r)||function(r){if("undefined"!=typeof Symbol&&null!=r[Symbol.iterator]||null!=r["@@iterator"])return Array.from(r)}(r)||function(r,e){if(!r)return;if("string"==typeof r)return i(r,e);var n=Object.prototype.toString.call(r).slice(8,-1);"Object"===n&&r.constructor&&(n=r.constructor.name);if("Map"===n||"Set"===n)return Array.from(r);if("Arguments"===n||/^(?:Ui|I)nt(?:8|16|32)(?:Clamped)?Array$/.test(n))return i(r,e)}(r)||function(){throw new TypeError("Invalid attempt to spread non-iterable instance.\nIn order to be iterable, non-array objects must have a [Symbol.iterator]() method.")}()}function i(r,e){(null==e||e>r.length)&&(e=r.length);for(var n=0,t=new Array(e);n<e;n++)t[n]=r[n];return t}function s(r,e,n,t,o,a,i){try{var s=r[a](i),c=s.value}catch(r){return void n(r)}s.done?e(c):Promise.resolve(c).then(t,o)}var c="Motor";function l(r){var e=r.node;return(0,o.jsxs)(o.Fragment,{children:[(0,o.jsx)("h3",{children:"Motor"}),(0,o.jsx)("span",{className:"xsmall",children:"Control motors"}),(0,o.jsxs)(t.Select,{nodeId:e.id,name:"mode",value:"1",children:[(0,o.jsx)("option",{value:"FORWARD",children:"Forward"}),(0,o.jsx)("option",{value:"LEFT",children:"Turn Left"}),(0,o.jsx)("option",{value:"RIGHT",children:"Turn Right"}),(0,o.jsx)("option",{value:"REVERSE",children:"Reverse"}),(0,o.jsx)("option",{value:"BRAKE",children:"Brake"})]}),(0,o.jsx)(t.NumberInput,{nodeId:e.id,name:"speed",value:"50"}),e.State.err&&(0,o.jsx)(o.Fragment,{children:(0,o.jsx)("span",{style:{margin:"0.25rem",color:"var(--red)"},children:e.State.err})})]})}function u(r){return d.apply(this,arguments)}function d(){var r;return r=function*(r){var e,n,t=r.node,o=r.controller,i=r.inputs.socket,s=r.state,c=s.mode,l=s.speed;switch(c){case"FORWARD":e=new Uint8Array([l]),n=new Uint8Array([l]);break;case"LEFT":e=new Uint8Array([l]),n=new Uint8Array([l/5]);break;case"RIGHT":e=new Uint8Array([l/5]),n=new Uint8Array([l]);break;case"REVERSE":e=new Uint8Array([-l]),n=new Uint8Array([-l]);break;case"BRAKE":e=new Uint8Array([0]),n=new Uint8Array([0])}var u=new Uint8Array([192].concat(a(e),a(n)));if(console.log(u),!i)return t.State.err="Socket is not connected...",o.update(t),o.trigger(0);i.send(u);var d=yield new Promise((function(r){i.onmessage=function(e){r(e)}}));return console.log(d),o.trigger(0)},d=function(){var e=this,n=arguments;return new Promise((function(t,o){var a=r.apply(e,n);function i(r){s(a,t,o,i,c,"next",r)}function c(r){s(a,t,o,i,c,"throw",r)}i(void 0)}))},d.apply(this,arguments)}var p=[n.port.input().type("trigger"),n.port.input().type("data").label("socket"),n.port.output().type("trigger")],y=e.VG,f=e.xz,m=e.ZP,v=e.Tt;export{y as Name,f as Trigger,m as default,v as ports};