################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/home/vityha/ti/ccs1100/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/bin/cl430" -vmspx --code_model=small --use_hw_mpy=F5 --include_path="/home/vityha/ti/ccs1100/ccs/ccs_base/msp430/include" --include_path="/home/vityha/Documents/УКУ/POC/nonvolatile_thermometer/ccs_workspace/eusci_b_i2c_ex1_masterRxMultiple" --include_path="/home/vityha/Documents/УКУ/POC/nonvolatile_thermometer/ccs_workspace/eusci_b_i2c_ex1_masterRxMultiple/driverlib/MSP430FR2xx_4xx" --include_path="/home/vityha/ti/ccs1100/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/include" --advice:power="none" --advice:hw_config=all --define=DEPRECATED --define=__MSP430FR2433__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


