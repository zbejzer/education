# ------------------------------------------------------------
# Wygeneruj 1000 prób 100-elementowych: x_1, ..., x_20 z rozkładu X ~ N(0, 1). 
# Oblicz dla każdej z nich sumę kwadratów y = x_1^2 + ... + x_20^2. Narysuj 
# na jednym rysunku histogram danych y_1, ..., y_1000 oraz wykres gęstości 
# rozkładu chi-kwadrat chi^2(20). Poeksperymentuj z innymi parametrami 
# i długościami prób.
# ------------------------------------------------------------

set.seed(123)

rysuj_chi2 <- function(N = 1000, k = 20, breaks = "Sturges") {
  
  x <- matrix(rnorm(N * k, mean = 0, sd = 1), nrow = N, ncol = k)
  y <- rowSums(x^2)
  
  hist(y,
       breaks = breaks,
       freq   = FALSE,
       col    = "lightblue",
       border = "white",
       main   = sprintf("chi^2(%d): N = %d prób", k, N),
       xlab   = "y",
       ylab   = "gęstość")
  
  curve(dchisq(x, df = k),
        from = min(y), to = max(y),
        n = 500, add = TRUE, col = "red", lwd = 2)
  
  legend("topright",
         legend = c("histogram próby", "gęstość chi^2"),
         fill   = c("lightblue", NA),
         border = c("white", NA),
         lty    = c(NA, 1), lwd = c(NA, 2),
         col    = c(NA, "red"),
         bty    = "n")
  
  invisible(y)
}

rysuj_chi2(N = 1000, k = 20)

op <- par(mfrow = c(2, 3))

rysuj_chi2(N = 100,    k = 20)
rysuj_chi2(N = 1000,   k = 20)
rysuj_chi2(N = 100000, k = 20, breaks = 60)

rysuj_chi2(N = 1000, k = 1)
rysuj_chi2(N = 1000, k = 5)
rysuj_chi2(N = 1000, k = 50)
par(op)