import express from 'express';
import { join } from 'path';

const app = express();

app.use(express.static(join(__dirname, '..', 'client', 'dist')));

app.listen(3030);

console.log('Server listening on localhost:3030');