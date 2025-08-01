#include <libubus.h>
#include <libubox/blobmsg_json.h>
#include <stdio.h>
#include <unistd.h>

#include "find_ubus.h"

#define MY_OWN_SOCKET		"Scripts/hm.sock"

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

// TODO: Add another ubus method. Can be something that changes a value.
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
    //ctx = ubus_connect(NULL);
    ctx = ubus_connect(MY_OWN_SOCKET);
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
