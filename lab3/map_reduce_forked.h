//
// Created by isnob on 29/05/2020.
//

#ifndef LAB3_MAP_REDUCE_FORKED_H
#define LAB3_MAP_REDUCE_FORKED_H

#endif //LAB3_MAP_REDUCE_FORKED_H
#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>
template <typename MapperInputT, typename ResultT, typename ReducerInputT, typename M, typename R>
std::map<std::string, ResultT> map_reduce_fork(const std::string &inputf, M &mapfun, R &reducefun)
{
    std::string line;
    std::map<std::string, ResultT> results;

    std::ifstream ifs(inputf);
    // 0 read
    // 1 write
    int driverToMapper[2];
    int mapperToDriver[2];
    int driverToReducer[2];
    int reduceToDriver[2];

    pipe(driverToMapper);
    pipe(mapperToDriver);
    pipe(driverToReducer);
    pipe(reduceToDriver);

    pid_t childPid = fork();

    std::vector<char> buff;
    MessageT m;
    ResultT r;

    switch (childPid)
    {
        case -1:
            std::cout << "error" << std::endl;
            close(driverToMapper[0]);
            close(driverToMapper[1]);
            close(mapperToDriver[0]);
            close(mapperToDriver[1]);
            close(driverToReducer[0]);
            close(driverToReducer[1]);
            close(reduceToDriver[0]);
            close(reduceToDriver[1]);

            break;
        case 0:
            // MAPPER
            close(driverToMapper[1]);
            close(mapperToDriver[0]);
            std::cout << "mapper: waiting for message" << std::endl;
            buff = read_pipe(driverToMapper[0]);
            m.deserialize(buff);
            r = fun(m);
            write_pipe(childToParent[1], r.serialize());
            std::cout << "mapper: result sent" << std::endl;
            close(driverToMapper[0]);
            close(mapperToDriver[1]);
            break;
        default: // DRIVER

            pid_t secondChildPid = fork();

            switch (secondChildPid)
            {
                case -1: /* constant-expression */:
                    std::cout << "error second fork" << std::endl;
                    close(driverToMapper[0]);
                    close(driverToMapper[1]);
                    close(mapperToDriver[0]);
                    close(mapperToDriver[1]);
                    close(driverToReducer[0]);
                    close(driverToReducer[1]);
                    close(reduceToDriver[0]);
                    close(reduceToDriver[1]);
                    break;

                case 0: //REDUCER
                    close(driverToReducer[1]);
                    close(reducerToDriver[0]);
                    std::cout << "reducer: waiting for message" << std::endl;
                    buff = read_pipe(driverToReducer[0]);
                    m.deserialize(buff);
                    r = fun(m);
                    write_pipe(reducerToParent[1], r.serialize());
                    std::cout << "reducer: result sent" << std::endl;
                    close(driverToreducer[0]);
                    close(reducerToDriver[1]);
                    break;
                default: // DRIVER
                    close(parentToChild[0]);
                    close(childToParent[1]);
                    std::cout << "parent: sending message" << std::endl;
                    write_pipe(parentToChild[1], input.serialize());
                    buff = read_pipe(childToParent[0]);
                    r.deserialize(buff);
                    std::cout << "parent: result: " << r.res << std::endl;
                    close(parentToChild[1]);
                    close(childToParent[0]);
                    break;
            }
    }
}
