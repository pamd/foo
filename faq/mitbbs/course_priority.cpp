/* Suppose we have N courses that have dependency relationships. Each sememster we can only take K courses
 * at most. How to take these courses so that we can finish them in shortest time?
 * Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32149793.html
 * Q410.
 */

/* peking2: Greedy algorithm, python code:
class Node:
    def __init__(self, val):
        self.val=val
        self.In=set()
        self.Out=set()
    def __cmp__(self, other):
        if len(self.Out)<len(other.Out):
            return 1
        elif len(self.Out)>len(other.Out):
            return -1
        else:
            return 0
    def __str__(self):
        return self.val+":"+str(self.In)+":"+str(self.Out)
    
courses=[['D','A'],['D','B'],['E','B'],['F','A'],['F','C'],['H','B'],['I','A
'],['I','D']]
dict={}
for i in courses:
    a=i[0]
    b=i[1]
    if not dict.has_key(a):
        dict[a]=Node(a)
    if not dict.has_key(b):
        dict[b]=Node(b)
    
    dict[a].In.add(b)
    dict[b].Out.add(a)

hq=[]
for i in dict.keys():
    if len(dict[i].In)==0:
        heappush(hq,dict[i])

k=2 #2 courses each semester
sem=1
count=min(k,len(hq))

while len(hq)!=0:
    n=heappop(hq)
    print "semester"+str(sem)+":"+n.val
    for i in n.Out:
        dict[i].In.remove(n.val)
        if len(dict[i].In)==0:
            heappush(hq,dict[i])
    count-=1
    if count==0:
        sem+=1
        count=min(k,len(hq))
    
*/
