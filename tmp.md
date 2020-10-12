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
&=\frac{n!}{2^D}\binom{D}{k}\times [z^n]
	(\sum_{i=0}^k\binom{k}{i} e^{z(i-(k-i))}(-1)^{k-i})
	(\sum_{i=0}^{D-k}\binom{D-k}{i} e^{z(i-(D-k-i))})\\
&=\frac{n!}{2^D}\binom{D}{k}\times [z^n]
	(\sum_{i=0}^k\binom{k}{i}e^{z(2i-k)}(-1)^{k-i})
	(\sum_{i=0}^{D-k}\binom{D-k}{i} e^{z(2i-D+k)})\\
&=\frac{n!}{2^D}\binom{D}{k}\times [z^n]
	\sum_{i=0}^k\sum_{j=0}^{D-k}\binom{k}{i}\binom{D-k}{j}(-1)^{k-i}e^{z(2i-k+2j-D+k)}\\
&=\frac{n!}{2^D}\binom{D}{k}\times [z^n]
	\sum_{i=0}^k\sum_{j=0}^{D-k}\binom{k}{i}\binom{D-k}{j}(-1)^{k-i}e^{z(2i+2j-D)}\\
&=\frac{1}{2^D}\binom{D}{k}\times
	\sum_{i=0}^k\sum_{j=0}^{D-k}\binom{k}{i}\binom{D-k}{j}(-1)^{k-i}(2i+2j-D)^n
\end{aligned}
$$

到这里已经可以$O(D^2)$计算一个$k$的贡献了,暴力搞起来就是$O(D^3)$.我们试试进一步优化.
$$
\begin{aligned}
&\frac{1}{2^D}\binom{D}{k}\times
	\sum_{i=0}^k\sum_{j=0}^{D-k}\binom{k}{i}\binom{D-k}{j}(-1)^{k-i}(2i+2j-D)^n\\
=&\frac{1}{2^D}
	\sum_{i=0}^k\sum_{j=0}^{D-k}\frac{D}{k!(D-k)!}\frac{k!}{i!(k-i)!}\frac{(D-k)!}{j!(D-k-j)!}(-1)^{k-i}(2i+2j-D)^n\\
=&\frac{1}{2^D}
	\sum_{i=0}^k\sum_{j=0}^{D-k}
		\frac{D!}{1}\frac{1}{i!(k-i)!}\frac{1}{j!(D-k-j)!}
		(-1)^{k-i}(2i+2j-D)^n\\
=&\frac{D!}{2^D}
	\sum_{j=0}^{D-k}
	\sum_{i=0}^k \frac{(-1)^{k-i}}{(k-i)!}
		\frac{(2i+2j-D)^n}{j!(D-k-j)!}\frac{1}{i!}\\
\end{aligned}
$$
