#!/usr/bin/env python3
'''
Created on 20200730
Update on 20200803
@author: Eduardo Pagotto
'''

import helloworld


def main():

    try:
        print(helloworld.hello())
        user = helloworld.createUser()
        print('--------')
        print(str(user))

        retorno = user.inicialize(2, 33)
        print(str(retorno))

        retorno = user.finalize(444, 5555)
        print(str(retorno))

    except Exception as exp:
        print('Erro: %s', str(exp))


if __name__ == "__main__":
    main()
