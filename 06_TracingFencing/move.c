#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

enum { 
    BUF = 1024,


    NO_ERR = 0b0,
    ERR_OPEN_SRC = 0b1,
    ERR_OPEN_DEST = 0b10,
    ERR_RD = 0b100,
    ERR_WR = 0b1000,
    ERR_CLOSE_SRC = 0b10000,
    ERR_CLOSE_DEST = 0b100000,
    ERR_UNLINK_SRC = 0b1000000,
    ERR_UNLINK_DEST = 0b10000000
};

int safe_close(int fd) {
    if(close(fd) == -1) {
        printf("cannot close file\n");
        return 1;
    }

    return 0;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("unsupported number of arguments (2 expexted)\n");
        return 0;
    }

    int origin = open(argv[1], O_RDONLY);
    if (origin == -1) {
        printf("cannot open source file %s\n", argv[1]);
        return ERR_OPEN_SRC;
    }

    int dest = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (origin == -1) {
        printf("cannot open/create destination file %s\n", argv[2]);
        return ERR_OPEN_DEST;
    }

    char buf[BUF];
    ssize_t write_bytes;
    ssize_t read_bytes = read(origin, buf, sizeof(buf));

    while (read_bytes > 0) {
        write_bytes = write(dest, buf, read_bytes);
        if (write_bytes == -1) {
            printf("error on writing file %s\n", argv[2]);
            int err = ERR_WR;

            if(safe_close(origin)) {
                err |= ERR_CLOSE_SRC;
            }

            if(safe_close(dest)) {
                err |= ERR_CLOSE_DEST;
            }

            if(unlink(argv[2]) == -1)  {
                printf("error on unlinking file %s\n", argv[1]);
        
                err |= ERR_UNLINK_DEST;
            }

            return err;
        }

        read_bytes = read(origin, buf, sizeof(buf));
    }

    if(read_bytes == -1) {
        printf("error on reading file %s\n", argv[1]);
        int err = ERR_RD;

        if(safe_close(origin)) {
            err |= ERR_CLOSE_SRC;
        }
        if(safe_close(dest)) {
            err |= ERR_CLOSE_DEST;
        }

        if(unlink(argv[2]) == -1)  {
            printf("error on unlinking file %s\n", argv[1]);

            err |= ERR_UNLINK_DEST;
        }

        return err;
    }

    if(safe_close(origin)) {
        return ERR_CLOSE_SRC;
    }

    if(safe_close(dest)) {
        return ERR_CLOSE_DEST;
    }
    
    int unlinked = unlink(argv[1]);

    if(unlinked == -1) {
        printf("error on unlinking file %s\n", argv[1]);
        
        return ERR_UNLINK_SRC;
    }

    return 0;
}
