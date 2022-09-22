# Windows HTTP Server (W8Server)

## Usage

```c++
http_server::HTTPServer svr{};

svr.set_port(8080);  // It is 8080 by default
svr.init();  // Initialize TCP server

auto return_message = "Have a nice day!";

svr.on_get("/", [&](auto req) {  // Set callback for endpoint "/"
    http_server::HTTPResponse res{};

    res.status = 200;
    res.status_message = "Success";
    res.headers.insert({"Content-Type", "text/plain"});
    res.headers.insert({"Content-Length", std::to_string(return_message.size())});
    res.body = return_message;

    return res;
});

svr.run();  // Listenning to requests
```
