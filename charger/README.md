# ASUS Zenfone 2 Laser (ZE550KL) Downstream Charger Driver Breakdown

The driver used by ASUS is not found in the android common kernels or any downstream kernel. So probably it's a custom driver modified by asus.


# Device Tree

[**msm-pm8916.dtsi**](https://github.com/antony-jr/postmarketos-asus-z00l/blob/master/charger/msm-pm8916.dtsi)

```
&spmi_bus {
        qcom,pm8916@0 {
                spmi-slave-container;
                reg = <0x0>;
                #address-cells = <1>;
                #size-cells = <1>;

                pm8916_revid: qcom,revid@100 {
                        compatible = "qcom,qpnp-revid";
                        reg = <0x100 0x100>;
                };
		
		...

                pm8916_vadc: vadc@3100 {
                        compatible = "qcom,qpnp-vadc";
                        reg = <0x3100 0x100>;
                        #address-cells = <1>;
                        #size-cells = <0>;
                        interrupts = <0x0 0x31 0x0>;
                        interrupt-names = "eoc-int-en-set";
                        qcom,adc-bit-resolution = <15>;
                        qcom,adc-vdd-reference = <1800>;
                        qcom,vadc-poll-eoc;
                        qcom,pmic-revid = <&pm8916_revid>;

                        chan@8 {
                                label = "die_temp";
                                reg = <8>;
                                qcom,decimation = <0>;
                                qcom,pre-div-channel-scaling = <0>;
                                qcom,calibration-type = "absolute";
                                qcom,scale-function = <3>;
                                qcom,hw-settle-time = <0>;
                                qcom,fast-avg-setup = <0>;
                        };

                        chan@9 {
                                label = "ref_625mv";
                                reg = <9>;
                                qcom,decimation = <0>;
                                qcom,pre-div-channel-scaling = <0>;
                                qcom,calibration-type = "absolute";
                                qcom,scale-function = <0>;
                                qcom,hw-settle-time = <0>;
                                qcom,fast-avg-setup = <0>;
                        };

                        chan@a {
                                label = "ref_1250v";
                                reg = <0xa>;
                                qcom,decimation = <0>;
                                qcom,pre-div-channel-scaling = <0>;
                                qcom,calibration-type = "absolute";
                                qcom,scale-function = <0>;
                                qcom,hw-settle-time = <0>;
                                qcom,fast-avg-setup = <0>;
                        };
                };

                pm8916_adc_tm: vadc@3400 {
                        compatible = "qcom,qpnp-adc-tm";
                        reg = <0x3400 0x100>;
                        #address-cells = <1>;
                        #size-cells = <0>;
                        interrupts =    <0x0 0x34 0x0>,
                                        <0x0 0x34 0x3>,
                                        <0x0 0x34 0x4>;
                        interrupt-names =       "eoc-int-en-set",
                                                "high-thr-en-set",
                                                "low-thr-en-set";
                        qcom,adc-bit-resolution = <15>;
                        qcom,adc-vdd-reference = <1800>;
                        qcom,adc_tm-vadc = <&pm8916_vadc>;
                        qcom,pmic-revid = <&pm8916_revid>;
                };

                pm8916_chg: qcom,charger {
                        spmi-dev-container;
                        compatible = "qcom,qpnp-linear-charger";
                        #address-cells = <1>;
                        #size-cells = <1>;

                        qcom,vddmax-mv = <4200>;
                        qcom,vddsafe-mv = <4200>;
                        qcom,vinmin-mv = <4308>;
                        qcom,ibatsafe-ma = <1440>;
                        qcom,thermal-mitigation = <1440 720 630 0>;
                        qcom,cool-bat-decidegc = <100>;
                        qcom,warm-bat-decidegc = <450>;
                        qcom,cool-bat-mv = <4100>;
                        qcom,warm-bat-mv = <4100>;
                        qcom,ibatmax-warm-ma = <360>;
                        qcom,ibatmax-cool-ma = <360>;
                        qcom,batt-hot-percentage = <25>;
                        qcom,batt-cold-percentage = <80>;
                        qcom,tchg-mins = <232>;
                        qcom,chg-vadc = <&pm8916_vadc>;
                        qcom,chg-adc_tm = <&pm8916_adc_tm>;

                        status = "disabled";

                        qcom,chgr@1000 {
                                reg = <0x1000 0x100>;
                                interrupts =    <0x0 0x10 0x7>,
                                                <0x0 0x10 0x6>,
                                                <0x0 0x10 0x5>,
                                                <0x0 0x10 0x0>;
                                interrupt-names =       "chg-done",
                                                        "chg-failed",
                                                        "fast-chg-on",
                                                        "vbat-det-lo";
                        };

                        qcom,bat-if@1200 {
                                reg = <0x1200 0x100>;
                                interrupts =    <0x0 0x12 0x1>,
                                                <0x0 0x12 0x0>;
                                interrupt-names =       "bat-temp-ok",
                                                        "batt-pres";
                        };

                        qcom,usb-chgpth@1300 {
                                reg = <0x1300 0x100>;
                                interrupts =    <0 0x13 0x4>,
                                                <0 0x13 0x2>,
                                                <0 0x13 0x1>;
                                interrupt-names =       "usb-over-temp",
                                                        "chg-gone",
                                                        "usbin-valid";
                        };

                        qcom,chg-misc@1600 {
                                reg = <0x1600 0x100>;
                        };
                };

                pm8916_bms: qcom,vmbms {
                        spmi-dev-container;
                        compatible = "qcom,qpnp-vm-bms";
                        #address-cells = <1>;
                        #size-cells = <1>;
                        status = "disabled";

                        qcom,v-cutoff-uv = <3400000>;
                        qcom,max-voltage-uv = <4200000>;
                        qcom,r-conn-mohm = <0>;
                        qcom,shutdown-soc-valid-limit = <100>;
                        qcom,low-soc-calculate-soc-threshold = <15>;
                        qcom,low-voltage-calculate-soc-ms = <1000>;
                        qcom,low-soc-calculate-soc-ms = <5000>;
                        qcom,calculate-soc-ms = <20000>;
                        qcom,volatge-soc-timeout-ms = <60000>;
                        qcom,low-voltage-threshold = <3450000>;
                        qcom,s3-ocv-tolerence-uv = <1200>;
                        qcom,s2-fifo-length = <5>;
                        qcom,low-soc-fifo-length = <2>;
                        qcom,bms-vadc = <&pm8916_vadc>;
                        qcom,bms-adc_tm = <&pm8916_adc_tm>;
                        qcom,pmic-revid = <&pm8916_revid>;

                        qcom,force-s3-on-suspend;
                        qcom,force-s2-in-charging;
                        qcom,report-charger-eoc;
                        qcom,resume-soc = <99>;

                        qcom,batt-pres-status@1208 {
                                reg = <0x1208 0x1>;
                        };

                        qcom,qpnp-chg-pres@1008 {
                                reg = <0x1008 0x1>;
                        };

                        qcom,vm-bms@4000 {
                                reg = <0x4000 0x100>;
                                interrupts =    <0x0 0x40 0x0>,
                                                <0x0 0x40 0x1>,
                                                <0x0 0x40 0x2>,
                                                <0x0 0x40 0x3>,
                                                <0x0 0x40 0x4>,
                                                <0x0 0x40 0x5>;

                                interrupt-names = "leave_cv",
                                                  "enter_cv",
                                                  "good_ocv",
                                                  "ocv_thr",
                                                  "fifo_update_done",
                                                  "fsm_state_change";
                        };
                };

                pm8916_green_leds: qcom,leds@a100 {
                        compatible = "qcom,leds-qpnp";
                        reg = <0xa100 0x100>;
                        label = "mpp";
                };

                pm8916_red_leds: qcom,leds@a300 {
                        compatible = "qcom,leds-qpnp";
                        reg = <0xa300 0x100>;
                        label = "mpp";
                        pwms = <&pm8916_pwm 0 0>;
                };
        };
 ...
}

```

Which is included in the device's main device tree and used like 
this,


[**msm8916-mtp-ze550kl.dtsi**](https://github.com/antony-jr/postmarketos-asus-z00l/blob/master/charger/msm8916-mtp-ze550kl.dtsi)

```
&pm8916_chg {
        status = "ok";
        qcom,charging-disabled;
};

/ {
        mtp_batterydata: qcom,battery-data {
                qcom,rpull-up-kohm = <100>;
                qcom,vref-batt-therm = <1800000>;

                #include "ASUS-ZE550KL-3000mah-NVT+ATL.dtsi"
                #include "ASUS-ZE550KL-3000mah-SMT+COS.dtsi"
                #include "ASUS-ZE550KL-3000mah-SONY.dtsi"
        };
};

&pm8916_bms {
        status = "ok";
        qcom,battery-data = <&mtp_batterydata>;
};
```


# SMB358 Charger 


```
i2c@78b8000 { /* BLSP1 QUP4 */
    ...
 
    qcom_smb358_i2c@6a {
        compatible = "qcom,smb358-charger";
           reg = <0x6a>;
           pinctrl-names = "smb358_nfc_disable_active","smb358_nfc_disable_suspend";
           pinctrl-0 = <&nfc_disable_active>;
           pinctrl-1 = <&nfc_disable_suspend>;
           qcom,otg-gpio = <&msm_gpio 121 0x0>;
           qcom,inok-gpio = <&msm_gpio 20 0x0>;
   };
}
```
