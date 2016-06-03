import http from 'http';

const server = http.createServer();

server.listen(3030, () => console.log('Server listening on localhost:3030'));

export default server;