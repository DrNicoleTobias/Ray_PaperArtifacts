library(ggplot2)
library(grid)
library(gridExtra)
library(signal)

plot_trace <- function(column, data, row, axis_element, ylimits, disp_name) {

  print(c("Plotting ",column))
  g <- ggplot(data, aes_string(x=row, y=column))+
        geom_line(aes_string(x=row, y=column))+
        expand_limits(y = ylimits) +
        xlab("Time (s)")+
        scale_y_continuous(name=disp_name, breaks=seq(ylimits[1], ylimits[2], (ylimits[2]-ylimits[1])/1))

  if (!axis_element) {
      g <- g+ theme(axis.title.x =element_blank(),
                  axis.text.x  =element_blank(),
                  axis.ticks.x =element_blank())
  }
  return(g)
}

filter_and_decimate <- function(vector, dfactor) {
  filt_type <- "fir"
  filt_n <- 26
  offset <- vector[1]
  result = pmax(decimate(vector-offset,dfactor, n=filt_n, ftype=filt_type)+offset,0)
  return(result)
}


outputfilename <- "spotlight.pdf"
rawdata1 <- read.csv("../data/Harsh_spotlight.csv", header=TRUE)
rawdata2 <- read.csv("../data/Harsh_Spotlight_Through.csv", header=TRUE)
dfactor <- 100

columns <- c("Time","C")

plotdata1 <- ''
plotdata2 <- ''

for (column in columns) {
  print(column)
  column_values1 <- filter_and_decimate(rawdata1[,column],dfactor)
  column_values2 <- filter_and_decimate(rawdata2[,column],dfactor)
  if (plotdata1 != '') {
    plotdata1[column] <- column_values1
  } else {
    plotdata1 <- data.frame(column_values1)
  }

  if (plotdata2 != '') {
    plotdata2[column] <- column_values2
  } else {
    plotdata2 <- data.frame(column_values2)
  }
}


colnames(plotdata1) <- columns
colnames(plotdata2) <- columns


across <- plot_trace("C",plotdata1,"Time",FALSE, c(5,5.3), "Solar Panel OP (V)")
through <- plot_trace("C",plotdata2,"Time",TRUE, c(5,5.3), "Solar Panel OP (V)")


plots <- list(across, through);



g <- arrangeGrob(grobs=plots, ncol=1, heights=c(1,1.4))

ggsave(outputfilename, width=4, height=4, pointsize=18, device=cairo_pdf,g);
