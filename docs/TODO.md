# TODO

## Basic

- [x] TCPServer class;

- [ ] HTTPServer class;
    - [x] Target parser;
        - [x] Normalize target;
    - [ ] Query parameters parser;
    - [x] Route based callback system;
        - [x] Normalize methods;

- [ ] Create response from file;
    - [ ] Load file and return the bytes in response;
    - [ ] Set mime from file extension;
    - [ ] Custom 404 page;

- [ ] Parse form data;
    - [ ] Multi-part data;

- [ ] HTTP message syntax checker;

## Security

- [ ] Basic auth;

- [ ] Limit requests per second;

- [ ] HTTPS

## Performance

- [ ] Multithreading;

- [ ] WebsocketServer class;

- [ ] QUIC Implementation;
    - [ ] UDPServer class;