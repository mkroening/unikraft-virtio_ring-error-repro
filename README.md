# Unikraft `virtio_ring.c` Error Reproduction

This repository reproduces the https://github.com/unikraft/unikraft/issues/853 `virtio_ring.c` error:

```terminal
Waiting for connections!
Writing!
Half-time break!
Break over!
[    3.335716] ERR:  [libkvmvirtio] <virtio_ring.c @  348> Available descriptor:0, Request2
[    3.338315] ERR:  [libkvmvirtio] <virtio_ring.c @  348> Available descriptor:0, Request2
Written everything!
Client served!
Waiting for connections!
```

This is a minimal server-client setup.
The server transmits 128 MiB to the client.
In the middle of the transmission, the server makes a short break.
Then the transmission continues, resulting in the error.

The error relies on a race condition.
It may trigger more or less often depending on:
- The size of the unikernel (e.g. adding musl to the binary makes it more frequent).
- The size of the buffer (bigger transmissions tend to cause errors more reliable).
- The pause (without pauses inbetween transmissions, the error won't show up).
- The speed of the QEMU network device (user mode emulation does not show the error, TAP devices do).

# How to Reproduce

1. Setup the TAP device.
   ```bash
   sudo ./setup_tap.sh
   ```
2. Start the server using Unikraft (using KraftKit).
   ```bash
   ./run_server.sh
   ```
3. From another terminal, start the client.
   ```bash
   ./run_client.sh
   ```
