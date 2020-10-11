## CTS2019 pearl



直接对序列$\vec x$本身计数困难,考虑对它的值域$c_k=\sum_{i=1}^n [x_i=k]$计数.
约束条件是
$$
\begin{cases}
\sum_{i=1}^{D} \lfloor\frac{c_i}{2}\rfloor \geq m\\
\sum_{i=1}^{D} c_i=n\\
\end{cases}
$$

一个$\vec{c}$的贡献是$\frac{n!}{\prod_{i=1}^{D}c_i !}$  

我们引入$\lfloor\frac{x}{2}\rfloor=\frac{x-(x\bmod 2)}{2}$对约束条件进行化简.
$$
\begin{aligned}
&\sum_{i=1}^{D} \lfloor\frac{c_i}{2}\rfloor
	=\sum_{i=1}^{D}\frac{c_i-(c_i\bmod 2)}{2}\geq m\\
&\iff \sum_{i=1}^{D} c_i-\sum_{i=1}^{D} (c_i\bmod 2)=n-\sum_{i=1}^{D}(c_i\bmod 2)\geq 2m\\
&\iff\sum_{i=1}^{D}(c_i\bmod 2) =\sum_{i=1}^{D}[1=c_i\bmod 2]\leq n-2m\\
\end{aligned}
$$

我们枚举$k=\sum_{i=1}^{D}[1=c_i\bmod 2]$即$\vec c$中的奇数(其中$k\leq n-2m\land k\leq D$),同时考虑其贡献.这里要使用生成函数了.  
如果$2\mid c_k$那么$c_k$对应的生成函数是$\sum_{i=0}^{\infty}\frac{z^i}{i!}[2\not \mid i]=\frac{e^z-e^{-z}}{2}$,否则是$\sum_{i=0}^{\infty}\frac{z^i}{i!}[2\mid i]=\frac{e^z+e^{-z}}{2}$,不同的$c_k$选择是独立的,把生成函数乘起来,其中有$k$个是第一种,$D-k$个是第二种. 最后$\sum_{i=1}^{D} c_i=n$的约束我们取乘积的$z^n$系数
$$
\begin{aligned}
&\begin{aligned}
P_k(z)&=\binom{D}{k}(\frac{e^z-e^{-z}}{2})^k(\frac{e^z+e^{-z}}{2})^{D-k}\\
&=\frac{\binom{D}{k}}{2^D}(e^z-e^{-z})^k(e^z+e^{-z})^{D-k}\\
\end{aligned}
\\
\newline 
&\to n![z^n]P_k(z)=\frac{n!}{2^D}\binom{D}{k}\times [z^n](e^z-e^{-z})^k(e^z+e^{-z})^{D-k}\\
&=n!\frac{D!}{2^D}\times [z^n]\frac{(e^z-e^{-z})^k}{k!}\frac{(e^z+e^{-z})^{D-k}}{(D-k)!}\\
\end{aligned}
$$

走到这里已经没法简易变形了,需要换一个方式来计算$k$个$[c_i\equiv 1(\bmod 2)$的$\vec c$的贡献,我们尝试进行容斥.  

**这里大概是能够直接通过技巧做的,但是我的水平不够,所以参考题解,换了容斥的式子**

设$U=\{1,2,3\dots D\}$表示$c_1,c_2\dots c_D$  
设$f(S)$表示$k\in S\iff [c_k\equiv 1(\bmod 2)]$的$\vec c$的贡献(恰好$S$).  
设$g(S)$表示$k\in S\implies [c_k\equiv 1(\bmod 2)]$的$\vec c$的贡献(至少$S$).  
有$g(S)=\sum_{T\supseteq S}f(T)$进行子集反演有$f(S)=\sum_{T\supseteq S}(-1)^{|T-S|}g(T)$.  
其中$g(S)=n![z^n]\ (\frac{e^z-e^{-z}}{2})^k (e^z)^{D-k}$其中$k=|S|$.
$$
\begin{aligned}
f(S)&=n![z^n]\ \sum_{T\supseteq S}(-1)^{|T-S|}g(T)\\
	&=n![z^n]\ \sum_{T\supseteq S}(-1)^{|T-S|}(\frac{e^z-e^{-z}}{2})^{|T|} (e^z)^{D-|T|}\\
	&=n![z^n]\ \sum_{i=|S|}^{D}(-1)^{i-|S|}\binom{D-|S|}{i-|S|}(\frac{e^z-e^{-z}}{2})^{i} (e^z)^{D-i}
\end{aligned}
$$
于是,贡献为
$$
\begin{aligned}
&\binom{D}{k}n![z^n]\ 
	\sum_{i=k}^{D}(-1)^{i-k}\binom{D-k}{i-k} (\frac{e^z-e^{-z}}{2})^{i} (e^z)^{D-i}\\
=&\binom{D}{k}n![z^n]\ 
	\sum_{i=0}^{D-k}(-1)^i \binom{D-k}{i} (\frac{e^z-e^{-z}}{2})^{i+k} (e^z)^{(D-k)-i}\\
=&\binom{D}{k}n![z^n]
	(\frac{e^z-e^{-z}}{2})^k\ 
	\sum_{i=0}^{D-k}(-1)^i \binom{D-k}{i} (\frac{e^z-e^{-z}}{2})^i (e^z)^{(D-k)-i}\\
=&\binom{D}{k}n![z^n]
	(\frac{e^z-e^{-z}}{2})^k\times(-\frac{e^z-e^{-z}}{2}+e^z)^{D-k}\\
=&\binom{D}{k}n![z^n]
	(\frac{e^z-e^{-z}}{2})^k\times(\frac{e^z+e^{-z}}{2})^{D-k}
\end{aligned}
$$

***wdnmd,它怎么回去了啊***