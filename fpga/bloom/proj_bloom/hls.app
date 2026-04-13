<AutoPilot:project xmlns:AutoPilot="com.autoesl.autopilot.project" top="krnl_bloom" name="proj_bloom">
    <files>
        <file name="../../krnl_bloom_test.cpp" sc="0" tb="1" cflags="-Wno-unknown-pragmas" csimflags="" blackbox="false"/>
        <file name="krnl_bloom.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
    </files>
    <solutions>
        <solution name="solution1" status=""/>
    </solutions>
    <Simulation argv="/home/bgc9yp/ReLev_Artifact/fpga/bloom/keys.txt">
        <SimFlow name="csim" setup="false" optimizeCompile="false" clean="true" ldflags="" mflags=""/>
    </Simulation>
</AutoPilot:project>

