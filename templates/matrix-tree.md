# 关于matrix-tree theorem(Kirchhoff's theorem)的记录

## reference

- [wikipedia](https://en.wikipedia.org/wiki/Kirchhoff%27s_theorem)
- [OI wiki](https://oi-wiki.org/graph/matrix-tree/)


## note

### prufer sequence

`prufer sequence`与`有标号无根树`是一一对应的,  
可以线性时间内进行互相转换. 

长度为$n-2$,值域为$[1,n]$的序列$a$,和$n$点的无标号无根树$T$一一对应,  
且$1+\sum_{i=1}^{n-2} [a_i=k]=deg(k)$  

> `tree->seq`
> 选择一个编号最小的叶子,记录与它唯一相邻的点,删掉这个叶子节点.  
> 重复这一过程$n-2$次,直到剩余$2$个点.  
> 
> `seq->tree`
> 类似`tree->seq`的做法,找最小编号叶子,删掉.
> 从prufer序列得到树上每个点的度数,找到$\min(\{x\ :\ deg(x)=1\})$,它应当与prufer序列中的第一个数字代表的节点相连.  
> 这两个点的度数减1. 剩余的序列继续这个操作.


### matrix-tree


#### for undirected graph

$$
\begin{aligned}
&{(D)}_{i,j}=[i=j]\sum_{e\in E,e\sim(i,v)} w_e\\
&{(A)}_{i,j}=\sum_{e\in E,e\sim (i,j)} w_e\\
&C=D-A\\
\newline
&\implies \forall i,j\quad C_{i,j}=\sum_{T\in \text{spanning-tree}(G)}\prod_{e\in T} w_e
\end{aligned}
$$


> 简单来说,度数矩阵是表示与`某点相连的所有边的权之和`,邻接矩阵表示`连接两点的所有边之和`  
> 这个形式非常好,可以求各种好东西,见[Luogu P5296 生成树计数](https://www.luogu.org/problemnew/show/P5296)  
> 
> > 小S 刚刚学习了生成树的知识，聪明的他想出了一个问题：
> > 给定一个 $n$ 个点的带权无向完全图，求其所有生成树权值的 $k$ 次方之和。
> > 定义一个树的权值，为其所有边权值和。
> > 
> > 因为他不会，所以你要来做这题。
> > 由于答案可能很大，请输出答案对 $998244353$ 取模的结果。
> > 输入格式
> > 
> > 第一行两个非负整数 $n,k$，意义如题目描述。
> > 接下来 $n$ 行，每行 $n$ 个整数，为这个带权无向完全图的邻接矩阵表示。
> > 设$w_{i,j}$表示矩阵的第$i$行第$j$列，保证：
> > $w_{i,i}=0$和$w_{i,j}=w_{j,i}$




#### for directed graph

***TODO***
