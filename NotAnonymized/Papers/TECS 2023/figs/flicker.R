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


outputfilename <- "flicker.pdf"
rawdata <- read.csv("../data/flicker_test.csv", header=TRUE)
dfactor <- 20

columns <- c("Time","Filtered","Unfiltered")

plotdata <- ''

for (column in columns) {
  print(column)
  column_values <- filter_and_decimate(rawdata[,column],dfactor)
  if (plotdata != '') {
    plotdata[column] <- column_values
  } else {
    plotdata <- data.frame(column_values)
  }
}


colnames(plotdata) <- columns


unfiltered <- plot_trace("Unfiltered",plotdata,"Time",FALSE, c(5.3,5.7), "Unfiltered (V)")
filtered <- plot_trace("Filtered",plotdata,"Time",TRUE, c(3.8,4.2), "Filtered (V)")


plots <- list(unfiltered, filtered);



g <- arrangeGrob(grobs=plots, ncol=1, heights=c(1,1.4))

ggsave(outputfilename, width=4, height=4, pointsize=18, device=cairo_pdf,g);
