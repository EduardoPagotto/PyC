#!/usr/bin/env python3
'''
Created on 20200730
Update on 20200803
@author: Eduardo Pagotto
'''

import helloworld


def main():
    print(helloworld.hello())
    val = helloworld.createUser()
    print(str(val))


if __name__ == "__main__":
    main()
