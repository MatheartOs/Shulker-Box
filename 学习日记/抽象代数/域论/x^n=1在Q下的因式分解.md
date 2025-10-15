# 多项式 $x^n-1$ 在 $\mathbb{Q}$ 下的因式分解

## 1. 结论

在有理数域 $\mathbb{Q}$ 下，$x^n-1$ 的因式分解为：

$$
x^n-1 = \prod_{d\mid n} \Phi_d(x)
$$

其中 $\Phi_d(x)$ 是 $d$ 次**本原$n$次单位根多项式**（$d$为$n$的正因子）。

## 2. 本原单位根多项式（Cyclotomic Polynomial）

- $\Phi_n(x)$ 的定义：
  $\Phi_n(x) = \prod_{\substack{1\leq k\leq n \\ \gcd(k,n)=1}} \left(x - e^{2\pi i k/n}\right)$
- $\Phi_n(x)$ 在 $\mathbb{Q}$ 上不可约。
- $x^n-1$ 的所有有理系数不可约因子就是 $\Phi_d(x)$。

## 3. 例子

- $x^6-1 = (x-1)(x+1)(x^2-x+1)(x^2+x+1)$
  - 其中 $\Phi_1(x)=x-1$
  - $\Phi_2(x)=x+1$
  - $\Phi_3(x)=x^2+x+1$
  - $\Phi_6(x)=x^2-x+1$

## 4. 证明思路

- $x^n-1$ 的所有根是 $n$ 次单位根。
- 每个 $n$ 次单位根属于唯一的 $\Phi_d(x)$，$d\mid n$。
- $\Phi_n(x)$ 在 $\mathbb{Q}$ 上不可约，且 $x^n-1$ 在 $\mathbb{Q}$ 上的所有不可约因子就是这些 $\Phi_d(x)$。

## 5. 详细证明过程

### 步骤1：$x^n-1$ 的根
$x^n-1=0$ 的所有根是 $n$ 次单位根：
$$
x_k = e^{2\pi i k/n}, \quad k=0,1,\ldots,n-1
$$

### 步骤2：本原单位根与本原多项式
- $n$ 次单位根中，$\gcd(k,n)=1$ 的 $x_k$ 称为本原 $n$ 次单位根。
- $\Phi_n(x)$ 的根正好是所有本原 $n$ 次单位根。

### 步骤3：$x^n-1$ 的因式分解
- $x^n-1$ 的所有根是所有 $d|n$ 的本原 $d$ 次单位根。
- 所以：
$$
x^n-1 = \prod_{d|n} \prod_{\substack{1\leq k\leq d \\ \gcd(k,d)=1}} (x - e^{2\pi i k/d}) = \prod_{d|n} \Phi_d(x)
$$

### 步骤4：$\Phi_n(x)$ 在 $\mathbb{Q}$ 上不可约
- $\Phi_n(x)$ 是 $x^n-1$ 在 $\mathbb{Q}$ 上的不可约因子。
- 这是代数数论中的经典结论。

### 步骤5：唯一性
- $x^n-1$ 在 $\mathbb{Q}$ 上的所有不可约因子就是 $\Phi_d(x)$，$d|n$。
- 因此 $x^n-1$ 在 $\mathbb{Q}$ 下的因式分解为 $\prod_{d|n} \Phi_d(x)$。

---

> 综上，$x^n-1$ 在 $\mathbb{Q}$ 下的因式分解为所有 $\Phi_d(x)$ 的乘积，$d$ 遍历 $n$ 的所有正因子。
