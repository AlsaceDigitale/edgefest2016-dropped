import ws from 'ws';
import server from './http';
import { LISTENERS } from './websockets-listeners';

const wss = new ws.Server({ server });

wss.on('connection', ws => {
    console.info('WebSockets: a client connected');

    ws.on('message', data => {
        let { action, payload } = JSON.parse(data);
        console.info(`WebSockets: [${action}]`, payload);

        LISTENERS[action] && LISTENERS[action](send, payload);
    })
});

export function send(action, payload = {}) {
    for(let client of wss.clients) {
        client.send(JSON.stringify({ action, payload }));
    }
}

export default wss;