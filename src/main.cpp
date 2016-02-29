#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <getopt.h>
#include "server.h"

int main(int argc, char* argv[])
{
    struct args_t {
        char *host; /* -h */
        char *port; /* -p */
        char *dir;  /* -d */
    } args;

    static const char *optString = "h:p:d:";
    static const struct option longOpts[] = {
        { "host", required_argument, NULL, 'h' },
        { "port", required_argument, NULL, 'p' },
        { "dir", required_argument, NULL, 'd' }
    };
    int longIndex;
    int opt;

    opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
    while( opt != -1 ) {
        switch( opt ) {
            case 'h':
                args.host = optarg; /* true */
                break;

            case 'p':
                args.port = optarg;
                break;

            case 'd':
                args.dir = optarg;
                break;

            default:
                break;
        }

        opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
    }

    if (pid_t pid = fork()) {
        if (pid > 0) {
            exit(0);
        }
        else {
            //сделать заптсь в лог
            return 1;
        }
    }

    setsid();
    chdir("/");
    umask(0);

    if (pid_t pid = fork()) {
        if (pid > 0) {
            exit(0);
        }
        else {
            //сделать заптсь в лог
            return 1;
        }
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    if (open("/dev/null", O_RDONLY) < 0) {
        // сделать запись в лог
        return 1;
    }

    if (open("/tmp/http_server.out", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0) {
        // сделать запись в лог
        return 1;
    }

    if (dup(1) < 0)
    {
      // сделать запись в лог
      return 1;
    }

  try
  {
    // Initialise the server.
//    std::size_t num_threads = boost::lexical_cast<std::size_t>(argv[3]);
    std::size_t num_threads = 2;
    http::server3::server s(args.host, args.port, args.dir, num_threads);

    // Run the server until stopped.
    s.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}
