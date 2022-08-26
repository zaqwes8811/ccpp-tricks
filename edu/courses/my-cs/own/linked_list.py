#!/usr/bin/python
#-*- coding: utf-8 -*-
'''
	abs. : ���������� ������������ ������
 
'''
import os
import sys

class Node:
    def __init__(self,value):
        self.data = value
        self.next = 0
 
class List:
    def __init__(self):
        self.firstNode = Node(0)  # ������� ���� ��� � ������������
 
    # ����������� �����
    def __ShowNodeData(self,aNode):
        if aNode.next != 0:
           print aNode.data
           self.__ShowNodeData(aNode.next)
 
    # �������� ���
    def Dump(self):
        self.__ShowNodeData(self.firstNode)
 
    # �������
    def InsertAfter(self,aNode,aNewNode):
        aNewNode.next = aNode.next
        aNode.next = aNewNode
 
    def InsertBeginning(self,aNewNode):
        aNewNode.next = self.firstNode
        self.firstNode = aNewNode    
 
# ��������� ����
nodeA = Node("A")
nodeB = Node("B")
nodeC = Node("C")
nodeD = Node("D")
 
# ������� ������ � ��������� ���
aList = List()
 
aList.InsertBeginning(nodeB)
aList.InsertAfter(nodeB,nodeD)
aList.InsertAfter(nodeD,nodeC)
aList.InsertAfter(nodeC,nodeA)
 
aList.Dump()
