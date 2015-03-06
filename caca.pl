$/ = '';            # paragraph read mode for readline access
print "mierda\n";
while (<ARGV>) {
    while (m#^START(.*?)^END#sm) {  # /s makes . span line boundaries
                                    # /m makes ^ match near newlines
        print "chunk $. in $ARGV has <<$1>>\n";
    }
}
