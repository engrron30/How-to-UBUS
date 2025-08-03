# UBus Learning

This repository aims to run and test UBUSD using Ubuntu Linux. ubus is typically executed in OpenWRT-based and this repo can serve as guide to simulate or experiment ubus in Linux-based terminal.

## How to Prepare Environment

### 1. Prepare dependencies.

Using __apt__, update and install the necessary dependencies in your machine.

    sudo apt update
    sudo apt install -y build-essential git libjson-c-dev libblobmsg-json-dev pkg-config

__[RECOMMENDED]__ Instead of manually pasting these commands on your terminal, you may use the shell script in this repo:

    ./Scripts/01_install-dependencies.sh


### 2. Prepare libubox and ubus code.

The _libubox_ and _ubus_ code are the vital part of the code to run ubusd. Their codebase can be collected in checking OpenWRT links by doing the following commands:
    
    git clone https://git.openwrt.org/project/libubox.git
    git clone https://git.openwrt.org/project/ubus.git

The cloning step can be done by manually running the script file below:

    ./Scripts/02_clone-repos.sh

__[RECOMMENDED]__ Fortunately, you do not have to do the steps above. After you clone this repo, the _libubox_ and _ubus_ code are already added in Packages directory.

### 3. Prepare your service code.

In the _Source_ directory, the _main.c_ file serves as the main program for hello service. This hello service intends to be registered in the ubus daemon, so that later, it can be called when someone triggers it in ubus. This service just prints hello as its message attribute value when triggered.

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

### 4. Build the Packages and Source

There are two main directories to compile in this repo: (a) _Packages_ and (b) _Source_. 

_Packages_ contain the needed OpenWRT-based code to run ubusd. To build the packages, go to _Packages_ directory then do _make_ command.

_Source_ is where our service code is located. To build the packages, go to _Source_ directory then do _make_ command. So, if you want to add your own service, add or modify file in _Source_ directory.

What happens when you do make in Source are the following commands but you do not need to manually type these because it is aready handled by Makefile for abstraction.
    
    gcc -o hello_service main.c \
        -I../libubox -I../ubus -I../Include \
        -L../libubox/build -lubox -lblobmsg_json \
        -L../ubus/build -lubus

__[RECOMMENDED]__ You can skip the above step for simplicity. Just do _make_ in the top directory and both Packages and Source are compiled.

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
