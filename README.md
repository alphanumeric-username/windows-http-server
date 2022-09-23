# W8Server (Windows HTTP Server)

Winsock based HTTP server for learning purposes.

## Usage example

```c++
w8s::HTTPServer svr{};
    
svr.set_port(8080);  // It is 8080 by default
svr.init();

std::string default_text { "Have a nice day!" };

std::string about_text { "This is a toy http server." };

svr.on_get("/", [&](auto req) {  // Set callback for "/" endpoint
    w8s::HTTPResponse res{};

    res.status = 200;
    res.status_message = "Success";
    res.headers.insert({"Content-Type", "text/plain"});
    res.headers.insert({"Content-Length", std::to_string(default_text.size())});
    res.body = default_text;

    std::cout << "Hit '/'\n";

    return res;
});

svr.on_get("/about/", [&](auto req) {  // Set callback for "/about" endpoint
    w8s::HTTPResponse res{};

    res.status = 200;
    res.status_message = "Success";
    res.headers.insert({"Content-Type", "text/plain"});
    res.headers.insert({"Content-Length", std::to_string(about_text.size())});

    res.body = about_text;

    std::cout << "Hit '/about'\n";

    return res;
});

svr.run();  // Start the server
```

### Building the example

>This process was only tested with MinGW-W64 GCC 11.3.0 compiler

Requirements:

- CMake 3.10 or higher;
- Winsock2;
- C++17 or higher;

At the root of the project type

    mkdir build && cd build && cmake .. && cmake --build .

Run the generated `w8svr.exe` executable.