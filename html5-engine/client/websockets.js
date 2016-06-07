import { LISTENERS } from './websockets-listeners';

const ws = new WebSocket('ws://localhost:3030');
const msgsBuffer = [];

ws.onopen = function() {
    console.info('WebSockets connection established');
    msgsBuffer.forEach(args => send(...args));

    send('hello');
};

ws.onclose = function() {
    console.error('WebSockets: connection closed');
};

ws.onmessage = function(message) {
    let { action, payload } = JSON.parse(message.data);

    LISTENERS[action] && LISTENERS[action](send, payload);
};

export function send(action, payload = {}) {
    if(ws.readyState == WebSocket.CONNECTING) {
        msgsBuffer.push(arguments);
        return;
    }

    ws.send(JSON.stringify({ action, payload }));
}
