# Python program to mirror an n-ary tree
 
# Represents a node of an n-ary tree
class Node :
 
    # Utility function to create a new tree node
    def __init__(self ,key):
        self.key = key 
        self.child = []
 
 
# Function to convert a tree to its mirror
def mirrorTree(root):
     
    # Base Case : nothing to do if root is None
    if root is None:
        return
     
    # Number of children of root 
    n = len(root.child)
 
    # If number of child is less than 2 i.e. 
    # 0 or 1 we don't need to do anything
    if n <2 :
        return
     
    # Calling mirror function for each child
    for i in range(n):
        mirrorTree(root.child[i]);
     
    # Reverse variable sized array of child pointers
    root.child.reverse()
     
 
# Prints the n-ary tree level wise
 
def printNodeLevelWise(root):
    if root is None:
        return
     
    # create a queue and enqueue root to it
    queue = []
    queue.append(root)
 
    # Do level order traversal. Two loops are used
    # to make sure that different levels are printed
    # in different lines
    while(len(queue) >0):
 
        n = len(queue)
        while(n > 0) :
 
            # Dequeue an item from queue and print it
            p = queue[0]
            queue.pop(0)
            print p.key,
     
            # Enqueue all children of the dequeued item
            for index, value in enumerate(p.child):
                queue.append(value)
 
            n -= 1
        print "" # Seperator between levels
         
 
# Driver Program
 
    """   Let us create below tree
    *              10
    *        /   /    \   \
    *        2  34    56   100
    *                 |   /  | \
    *                 1   7  8  9
    """
 
root = Node(10)
root.child.append(Node(2))
root.child.append(Node(34))
root.child.append(Node(56))
root.child.append(Node(100))
root.child[2].child.append(Node(1))
root.child[3].child.append(Node(7))
root.child[3].child.append(Node(8))
root.child[3].child.append(Node(9))
 
print "Level order traversal Before Mirroring"
printNodeLevelWise(root)
 
mirrorTree(root)
     
print "\nLevel Order traversal After Mirroring"
printNodeLevelWise(root)
