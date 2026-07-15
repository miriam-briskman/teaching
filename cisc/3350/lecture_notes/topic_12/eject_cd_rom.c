// The following program uses the CDROMEJECT request
//     to eject the media tray from a CDROM device,
//     which the user provides as the first argument
//     on the program’s command line.

// This program is taken from Linux System Programming:
//     Talking Directly to the Kernel and C Library, 
//     2nd Edition, by Love. ISNB: 978-1-44933953-1,
//     pages 282-283.

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/cdrom.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    int fd, ret;

    if (argc < 2)
    {
        fprintf (stderr,
                 "usage: %s <device to eject>\n",
                 argv[0]);
        exit (EXIT_FAILURE);
    }

    // Open the CD-ROM device, read-only.
    // O_NONBLOCK tells the kernel that we want to
    //    open the device even if there is no media
    //    present in the drive.
    fd = open (argv[1], O_RDONLY | O_NONBLOCK);
    if (fd < 0)
    {
        perror ("open");
        exit (EXIT_FAILURE);
    }

    // Send the eject command to the CD-ROM device:
    ret = ioctl (fd, CDROMEJECT, 0);
    if (ret)
    {
        perror ("ioctl");
        exit (EXIT_FAILURE);
    }

    ret = close (fd);
    if (ret)
    {
        perror ("close");
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
