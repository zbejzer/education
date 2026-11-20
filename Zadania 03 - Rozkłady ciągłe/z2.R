set.seed(123)

rysuj_chi2 <- function(n, k) {
  y <- rowSums(
    matrix(
      data = rnorm(n * k, mean = 0, sd = 1),
      nrow = n,
      ncol = k
    )^2
  )

  hist(
    y,
    freq = FALSE,
    main = paste0(
      "N = ",
      format(n, scientific = FALSE),
      ", k = ",
      format(k, scientific = FALSE)
    )
  )

  curve(expr = dchisq(x, df = k), add = TRUE, col = "red")
}

op <- par(mfrow = c(2, 3))

n <- c(100, 1000, 100000, 1000, 1000, 1000)
k <- c(20, 20, 20, 1, 5, 50)

for (i in seq_along(n)) {
  rysuj_chi2(n[i], k[i])
}

par(op)
