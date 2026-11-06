set.seed(123)

n <- c(10, 100)
alpha <- c(0.05, 0.5, 0.95)
x <- sapply(n, rnorm, mean = 0, sd = 1)

q_calc <- sapply(x, quantile, probs = alpha)
q_norm <- sapply(alpha, qnorm)

print(
  data.frame(
    n = c(n, "ref"),
    q_5 = c(q_calc[1, ], q_norm[1]),
    q_50 = c(q_calc[2, ], q_norm[2]),
    q_95 = c(q_calc[3, ], q_norm[3])
  )
)

x <- sapply(n, rexp, rate = 2)

q_calc <- sapply(x, quantile, probs = alpha)
q_norm <- sapply(alpha, qexp, rate = 2)

print(
  data.frame(
    n = c(n, "ref"),
    q_5 = c(q_calc[1, ], q_norm[1]),
    q_50 = c(q_calc[2, ], q_norm[2]),
    q_95 = c(q_calc[3, ], q_norm[3])
  )
)
