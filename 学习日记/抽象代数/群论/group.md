### 群的三大公理

$ \text{def: } (G,\circ) \text{ is a group} \iff $

1. **结合律**  
$\forall a, b, c \in G$:  
   $$(a \circ b) \circ c = a \circ (b \circ c)$$

1. **单位元**  
$\exist e \in G \text{, } \forall a \in G$:  
   $$e \circ a = a \circ e = a$$

1. **逆元**  
$\forall a \in G \text{, } \exists a^{-1} \in G$:  
   $$a \circ a^{-1} = a^{-1} \circ a = e$$ 
   $$  (a^{-1} 即为 a 的逆元) $$

---

### 群的陪集常见定理

1. **陪集划分定理**
   - 设$G$为群，$H$为$G$的子群，则$G$可以被$H$的所有不同左陪集（或右陪集）不交地划分。
   - 即$G = \bigsqcup_{i} a_i H$，其中$a_i H$为$H$的不同左陪集。

2. **陪集等势定理**
   - 任意左陪集$aH$的元素个数等于$H$的元素个数：$|aH| = |H|$。

3. **陪集相等充要条件**
   - $aH = bH$ 当且仅当 $a^{-1}b \in H$。
   - 换言之，$a$与$b$属于同一个左陪集当且仅当 $a^{-1}b \in H$。

4. **陪集与子群的交集**
   - 任意两个不同的左陪集$aH, bH$，要么不交，要么相等。
   - 即 $aH \cap bH = \varnothing$ 或 $aH = bH$。

5. **陪集个数与Lagrange定理**
   - $G$中$H$的左陪集个数为$[G : H]$，有$|G| = |H| \times [G : H]$。

6. **陪集与同构**
   - $H$的每个左陪集$aH$与$H$在集合意义下等势，但一般不构成群。

---

> 这些定理是群论中陪集理论的基础，广泛用于证明Lagrange定理、Sylow定理等。
