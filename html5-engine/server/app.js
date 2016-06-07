import express from 'express';
import { join } from 'path';
import server from './http';
import './websockets';

const app = express();

app.use(express.static(__dirname+'/../client/dist'));

server.on('request', app);

process.on('unhandledRejection', (reason, promise) => {
    console.error('Possibly Unhandled Rejection', promise, reason);
});
