set.seed(123)
rysuj_lognormal <- function(n, mu, sigma) {
  y <- rlnorm(n, meanlog = mu, sdlog = sigma)
  hist(
    y,
    freq = FALSE,
    breaks = 20,
    main = paste0(
      "n = ",
      format(n, scientific = FALSE),
      ", mu = ",
      format(mu, scientific = FALSE),
      ", sigma = ",
      format(sigma, scientific = FALSE)
    )
  )
  curve(expr = dlnorm(x, meanlog = mu, sdlog = sigma), add = TRUE, col = "red")
}

op <- par(mfrow = c(2, 3))

rysuj_lognormal(n = 100, mu = 0, sigma = 2)
rysuj_lognormal(n = 1000, mu = 0, sigma = 2)
rysuj_lognormal(n = 100000, mu = 0, sigma = 2)

rysuj_lognormal(n = 1000, mu = 0, sigma = 0.5)
rysuj_lognormal(n = 1000, mu = 1, sigma = 1)
rysuj_lognormal(n = 1000, mu = -1, sigma = 1.5)

par(op)
