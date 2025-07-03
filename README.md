# UBus Learning

This repository aims to run and test UBUSD using Ubuntu Linux. ubus is typically executed in OpenWRT-based platform which may be inconvenient for non-OpenWRT and Ubuntu user testing. The developer can use this guide as to trace the message coming from a service to the ubus daemon or simply ubusd.

**(1) Prepare dependencies.** You may skip this part depends on your machine.

    sudo apt update
    sudo apt install -y build-essential git libjson-c-dev libblobmsg-json-dev pkg-config

**(2) Prepare libubox.**
    
    git clone https://git.openwrt.org/project/libubox.git
    cd libubox
    mkdir build && cd build
    cmake -DBUILD_LUA=OFF ..
    make
    cd ../..

**(2) Prepare ubus code.** This time, you are going to build ubus with libubox dependencies.
    
    git clone https://git.openwrt.org/project/ubus.git
    cd ubus
    mkdir build && cd build
    cmake -DLIBUBOX_INCLUDE_DIR=../libubox -DLIBUBOX_LIBRARIES=../libubox/build -DBUILD_LUA=OFF ..
    make
    cd ../..

**(3) Prepare your service code:**
    
    mkdir my_program && cd my_program
    vim hello_service.c

    Hello Service Code:
        #include <libubus.h>
        #include <libubox/blobmsg_json.h>
        #include <stdio.h>

        static struct ubus_context *ctx;

        // Handler for the "say" method
        static int hello_handler(struct ubus_context *ctx, struct ubus_object *obj,
                         struct ubus_request_data *req, const char *method,
                         struct blob_attr *msg) {
            struct blob_buf b = {};
            blob_buf_init(&b, 0);
            blobmsg_add_string(&b, "message", "Hello from ubus!");
            ubus_send_reply(ctx, req, b.head);
            blob_buf_free(&b);
            return 0;
        }

        // Define the methods under "hello" object
        static const struct ubus_method hello_methods[] = {
            UBUS_METHOD_NOARG("say", hello_handler),
        };

        static struct ubus_object_type hello_type =
            UBUS_OBJECT_TYPE("hello_type", hello_methods);

        static struct ubus_object hello_object = {
            .name = "hello",
            .type = &hello_type,
            .methods = hello_methods,
            .n_methods = ARRAY_SIZE(hello_methods),
        };

        int main() {
            ctx = ubus_connect(NULL);
            if (!ctx) {
                fprintf(stderr, "Failed to connect to ubusd\n");
                return 1;
            }

            if (ubus_add_object(ctx, &hello_object)) {
                fprintf(stderr, "Failed to add ubus object\n");
                ubus_free(ctx);
                return 1;
            }

            printf("UBUS 'hello' object registered. Waiting for calls...\n");
            ubus_add_uloop(ctx);
            uloop_init();
            uloop_run();

            ubus_free(ctx);
            return 0;
        }

**(4) Compile the service source code:**
    
    gcc -o hello_service hello_service.c \
        -I../libubox -I../ubus \
        -L../libubox/build -lubox -lblobmsg_json \
        -L../ubus/build -lubus

In the latest commit, this GCC command line is now automated in the Makefile in _my_program_ directory. Instead of pasting this whole line to the terminal, just run the following:

    cd /my_program
    make

To remove the compiled file, just do:

    make clean

**(5) Run ubusd:**
    
    sudo ubusd &

If you are familiar how to start ubusd in your machine or an ubusd is already running in your devixe, you can skip some steps including this one (but don't skip 9).

**(6) Register hello object in ubus by running the server code.**
    
    sudo ./hello_service &

(7) List registered object in ubus:
    
    sudo ../ubus/build/ubus list

(8) Trigger hello from ubus:	
    
    sudo ../ubus/build/ubus call hello say

(9) Be awesome!
