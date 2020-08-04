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
        val = helloworld.createUser()
        print('--------')
        print(str(val))
    except Exception as exp:
        print('Erro: %s', str(exp))


if __name__ == "__main__":
    main()
