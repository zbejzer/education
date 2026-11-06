set.seed(123)

n <- c(10, 100)

op <- par(mfrow = c(2, 2))

x <- sapply(n, rnorm, mean = 0, sd = 1)
d <- sapply(x, ecdf)

for (i in 1:2) {
  plot(ecdf(x[[i]]), main = paste0("norm n = ", n[i]))
  curve(pnorm(x, mean = 0, sd = 1), add = TRUE, col = "red")
}

x <- sapply(n, rexp, rate = 2)
d <- sapply(x, ecdf)

for (i in 1:2) {
  plot(ecdf(x[[i]]), main = paste0("exp n = ", n[i]))
  curve(pexp(x, rate = 2), add = TRUE, col = "red")
}

par(op)
