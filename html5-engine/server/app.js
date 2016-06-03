import express from 'express';
import { join } from 'path';
import server from './http';
import './websockets';

const app = express();

app.use(express.static(__dirname+'/../client/dist'));

server.on('request', app);
