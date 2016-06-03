import ws from 'ws';
import server from './http';

const wss = new ws.Server({ server });

wss.on('connection', ws => {
    console.log('client connected');
});

export default wss;