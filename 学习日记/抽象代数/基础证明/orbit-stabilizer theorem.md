## 证明 轨道-稳定子定理 Orbit-Stabilizer Theorem

设有限群 $G$ 作用在集合 $X$ 上 <br>
轨道：
$$ G \cdot x = \{ g \cdot x \mid g \in G \} $$
稳定子：
$$ G_x = \{ g \in G \mid g \cdot x = x \} $$

$轨道-稳定子定理:$
$$ |G \cdot x| = \frac{|G|}{|G_x|} $$

---

### 证明：

移项得到：
$$ |G \cdot x| \cdot |G_x| = |G| $$

注意到其结构与 $拉格朗日定理$ 相似：
$$ |G:H| \cdot |H| = |G| $$
其中，$ H≤G, $ 即 $ H $ 为 $ G $ 的子群，$ |G:H| $ 为 $ H $ 在 $ G $ 中的左陪集数。
### 首先证明：$稳定子 G_x 为 G 的子群$：<br>
非空性：显然可知，存在单位元 $e \in G_x$ 使得 $e(x) = x$ <br>
封闭性：$\forall g_1,g_2 \in G_x$，$(g_1 \cdot g_2)(x) = g_1(g_2(x)) = g_1(x) = x$，即：$g_1 \cdot g_2 \in G_x$ <br>
逆元存在：若 $g \in G_x$，设：$g^{-1} \in G_x$， $g^{-1}(x) = g^{-1}(g(x)) = (g^{-1} \cdot g)(x) = e(x)$，即：$g^{-1} \cdot g = e$，$g^{-1}$ 是 $g$ 的逆元。<br>
因此，$G_x 为 G 的子群$。<br>

如果能证明：$|G \cdot x| = |G:G_x|$，那么根据拉格朗日定理，该结论显然成立。

### 证明：$|G \cdot x| = |G:G_x|$ <br>

考虑构造映射：
$$ \varphi:\quad G:G_x \to G \cdot x, \quad \varphi(gG_x) = g \cdot x$$
其中 $ G:G_x $ 是 $G_x$ 在 $G$ 中的左陪集集合。<br><br>
#### 考虑证明：$\varphi$ 为双射：<br>
$单射性$：设 $ g_1,g_2 \in G \cdot x $ 满足 $ g_1 \cdot x = g_2 \cdot x ,$ 则：
$$ g_2^{-1}g_1 \cdot x = x \implies g_2^{-1}g_1 \in G_x \implies g_1G_x = g_2G_x $$
因此 $ \varphi $ 为单射<br><br>
$满射性$：显然 $ \varphi $ 的像覆盖整个 $ G \cdot x $ 轨道，且对于任意 $ y \in G \cdot x, $ 都存在 $ g \in G $ 使得 $ g \cdot x = y, $ 所以：
$$ \varphi(gG_x) = y $$
因此 $ \varphi $ 为满射，即 $ \varphi $ 为双射，所以：
$$ |G \cdot x| = |G:G_x| $$

因此，根据拉格朗日定理：
$$ |G:G_x| \cdot |G_x| = |G| \implies |G \cdot x| \cdot |G_x| = |G| \implies |G \cdot x| = \frac{|G|}{|G_x|}$$
## 定理证毕 $\boxed{Q.E.D.}$