#!/usr/bin/awk -f

function style(kind, idx) {
    # Assigns style using node kind and index
    # First node is treated as a note
    if (idx == 0) {
        return ",shape=note,fontcolor=\"0.0 0.0 1.0\",style=filled,color=\"0.63 0.71 0.22\""
    }
    if (kind == "\"dict\"") {
        return ",shape=ellipse,nojustify=true,style=filled,color=\".7 .3 1.0\""
    } else if (kind == "\"list\""){
        return ",shape=rect,nojustify=true,fontcolor=\"0.0 0.0 1.0\",style=filled,color=\"0.06 0.99 0.3\""
    } else {
        return ",shape=box"
    }
}

function value(string, idx) {
    # Styles graph node values
    string = substr(string, 3, length(string)-3)
    s = gsub(/\s+/," ", string)
    s = gsub(/\\n/,"", string)
    s = gsub(/\\"/, "\"", string)
    if (length(string) > MAX_LIST_LEN) {
        string = substr(string, 0, MAX_LIST_LEN-5) "..." substr(string, length(string)-4, 5)
    }
    return string
}

BEGIN {
    edge_index = 0
    node_index = -1
    mono_font = "ubuntu"
    MAX_LIST_LEN = 40
}

# A node has: (name, label, style, value?)
# value is optional

/^node [0-9]+/ {
    node_index++
    nodes[node_index][0] = "\tnode_" $2 " "
    #print current_node
}

/name:/ {
    nodes[node_index][1] = substr($2, 2, length($2)-2)
    gsub(/\\"/, "\"",nodes[node_index][1])
} 

/kind:/ {
    kinds[node_index] = $2
    nodes[node_index][2] = style($2, node_index)
}

/value:/ {
    $1 = ""
    if (length(value($0, node_index)) > 0) {
        vrs = "<br/><font face=\"" mono_font "\">"
        vra = "</font>"
    } else {
        vrs = ""
        vra = ""
    }
    nodes[node_index][3] = vrs value($0) vra
}

/edge\s+[0-9]+\s+->\s+[0-9]+/ {
    edges[edge_index] = "\tnode_" $2 " -> " "node_" $4 
    edge_index++
}

END {
    print "digraph" nodes[0][0] " {"
    print "rankdir=LR;"
    for(i = 0; i <= node_index; i++) {
        print nodes[i][0] "[label=<<b>" nodes[i][1] "</b>" nodes[i][3] ">" nodes[i][2] "]"
    }
    print ""
    for(i = 0; i < edge_index; i++) {
        print edges[i]
    }
    print "}"
}
