# fibonacci
REST fibonacci test

This example REST API uses the libmicrohttpd package, which must be installed.
- - this allows a C/C++ program to act like a mini httpd server itself
- - in other words, no PHP/JAVA needed for this example

The following are expectation on the environment:
- - g++ compiler
- - curl for unit-tests


Makefile
- - the 'fibo_api' starts the code, you must specify some unused port e.g. "fibo_api 1234"

To unit-test and validate the code, see the 'tests' sub-directory:
- - the run_unit_tests will run a unit test validation on the fibo subroutine
    the fibo_api is not needed to be running for this test only
- - the run_url_tests will run the same test thru curl, and provides local end-to-end.
    the fibo_api must be running (i.e. in another terminal), and the port passed to it
    must match the port passed to run_url_tests

