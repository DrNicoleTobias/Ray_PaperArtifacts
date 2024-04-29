library(ggplot2)

fig_width = 6
fig_height = 3.5
args<-commandArgs(TRUE)
print(args)
bug_title = args[3]
outputfilename = args[2]
data = read.csv(args[1], header = TRUE)

curr_draw <- ggplot(data) +
         # The "Current" is actually Power I'm just too lazy to regen the data
         geom_line(aes(x=(Time), y=Raw_Facing_Inside), size=1) +
         theme_bw() +
         xlab("Time (s)") +
         ylab("Raw_Facing_Inside (V)") +
         ggtitle(bug_title) +
         theme(plot.margin=unit(c(0,4,0,0),"mm"),  # c(top, right, bottom, left), right margin to fit last axis label
          legend.position="none",
          plot.title = element_text(face="bold", size=19),
          axis.title = element_text(face="bold", size=18),
          axis.text = element_text(face="bold", size=14),
          strip.text = element_text(face="bold", size=12))
ggsave(outputfilename, plot=curr_draw, width=fig_width, height=fig_height, pointsize=16)#, device=cairo_ps) #, device=cairo_pdf);             