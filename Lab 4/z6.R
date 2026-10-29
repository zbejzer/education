n <- 1000
pareto <- function(x, a, b) ((a / b) * (b / (b + x)^(a + 1)))

lambda <- rgamma(n, shape = 10, rate = 1)
y <- sapply(X = lambda, FUN = rexp, n = 1)

op <- par(mfrow = c(1, 1))

hist(y, freq = FALSE, breaks = 30, xlim = c(0, 1))
curve(expr = pareto(x, 10, 1), col = "red", add = TRUE, from = 0)

par(op)
