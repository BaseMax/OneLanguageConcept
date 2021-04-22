.PHONY: clean All

All:
	@echo "----------Building project:[ one - Debug ]----------"
	@"$(MAKE)" -f  "one.mk"
clean:
	@echo "----------Cleaning project:[ one - Debug ]----------"
	@"$(MAKE)" -f  "one.mk" clean
