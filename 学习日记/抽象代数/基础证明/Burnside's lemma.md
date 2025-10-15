## 证明 伯恩赛德引理 Burnside's lemma

设有限群 $G$ 作用在集合 $X$ 上。 对于每个 $g \in G$，令 $ X^g $ 表示 $X$ 中在 $g$ 作用下不动的元素的集合，即
$$ X^g = \{ x \in X | g \cdot x = x \} $$
则轨道数量 $|X/G|$ 满足：
$$ |X/G| = \frac{1}{|G|} \sum_{g \in G}{|X^g|}$$

---

### 证明

不难发现直接对 $X^g$ 进行处理得不到足够发现，因此我们需要将 $\sum_{g \in G}{|X^g|}$ 转化为我们熟悉的形式。 </br>
不妨记 $(g,x)$ 为 $G$ 和 $X$ 中分别取一个元素组成的二元组，发现：
$$ \sum_{g \in G}{|X^g|} \quad 即为所有满足g \cdot x = x 的(g,x)的计数 $$
进行交换次序得到：
$$ \sum_{x \in X}{|G^x|} \quad 也为所有满足g \cdot x = x 的(g,x)的计数 $$
因此：
$$ \sum_{g \in G}{|X^g|} = \sum_{x \in X}{|G^x|} $$

我们对 $X$ 进行轨道拆分，假设 $X$ 在 $G$ 作用下的轨道数量为 $k$，因此我们可以将集合 $X$ 分为 $k$ 个不相交的轨道的集合：
$$ \{ \mathcal{O}_1,\mathcal{O}_2, \dots, \mathcal{O}_k \} $$
类似地，将表达式展开：
$$ \sum_{x \in X}{|G^x|} = \sum_{i=1}^{k}{\sum_{x \in \mathcal{O}_i}{|G^x|}} $$
又因为，对于同一条轨道 $\mathcal{O}_i$ 中的每个元素 $x$，其轨道大小 $Orb(x)$ 都是相等的，即 
$$\forall x \in \mathcal{O}_i,\quad Orb(x) = |\mathcal{O}_i|$$
（这条概念其实是显然的，只不过这里需着重强调以加深对于后续证明的理解） </br>
根据 $轨道-稳定子定理$：
$$ |\mathcal{O}_i| = \frac{|G|}{|G_x|} $$
不难发现，对于同一条轨道 $\mathcal{O}_i$ 中的每个元素 $x$，其稳定子大小 $|G^x|$ 是相等的，因此，$\sum_{x \in \mathcal{O}_i}{|G^x|}$ 实际上就是轨道 $\mathcal{O}_i$ 的大小与其中代表元(轨道中的任意一个$x$)的稳定子 $G^x$ 的大小的乘积，即
$$ \sum_{x \in \mathcal{O}_i}{|G^x|} = |\mathcal{O}_i| \cdot |G^x| = |G| （由轨道-稳定子定理） $$
代入上式得到：
$$ \sum_{x \in X}{|G^x|} = \sum_{i=1}^{k}{\sum_{x \in \mathcal{O}_i}{|G^x|}} = \sum_{i=1}^{k}{|G|} = k \cdot |G| $$
因此
$$ \sum_{g \in G}{|X^g|} = \sum_{x \in X}{|G^x|} = k \cdot |G| $$
移项得
$$ k = \frac{1}{|G|} \sum_{g \in G}{|X^g|} $$
其中，$k$ 即为轨道数量，代入 $k = |X/G|$ 得
$$ |X/G| = \frac{1}{|G|} \sum_{g \in G}{|X^g|}$$

该式即为 $Burnside引理$ </br>
### 至此，引理证毕！