n <- 1000
k <- 10

lambda <- 2

y <- replicate(n, expr = sum(rexp(k, rate = lambda)))

op <- par(mfrow = c(1, 1))

hist(
  y,
  freq = FALSE,
  breaks = 20,
  xlim = c(0, 14),
  ylim = c(0, 0.3)
)

curve(
  expr = dgamma(x, shape = k, rate = lambda),
  add = TRUE,
  col = "red",
)

par(op)
