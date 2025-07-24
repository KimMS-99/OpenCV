# 하위 디렉토리 중 Makefile이 있는 폴더를 자동으로 찾음
SUBDIRS := $(shell find . -mindepth 2 -name Makefile -exec dirname {} \;)

# all, clean은 실제 파일이 아닌 명령임을 선언
.PHONY: all clean

# 전체 빌드
all:
	@echo "🔧 최상위 Makefile 빌드 시작"
	@for dir in $(SUBDIRS); do \
		echo "📂 빌드 중: $$dir"; \
		$(MAKE) -C $$dir; \
	done
	@echo "✅ 전체 빌드 완료!"
	
# 전체 클린
clean:
	@echo "🔧 하위 디렉토리 클린 시작"
	@for dir in $(SUBDIRS); do \
		if [ -f $$dir/Makefile ]; then \
			echo "🧽 Cleaning $$dir..."; \
			$(MAKE) -C $$dir clean; \
		fi \
	done
	@echo "✅ 전체 clean 완료!"

# 특정 디렉토리의 run 타겟 실행
# 이 규칙은 'make run_디렉토리명_하위디렉토리명' 형식으로 호출될 때 동작합니다.
# 예시: make run_Ch8_P379
#
# 동작 방식:
# 1. 'run_' 접두사를 제거하고, 나머지 부분의 언더스코어('_')를 슬래시('/')로 변환하여
#    실제 디렉토리 경로를 생성합니다. (예: 'Ch8_P379' -> 'Ch8/P379')
# 2. 해당 디렉토리로 이동하여 (make -C [디렉토리 경로])
# 3. 해당 디렉토리의 Makefile에 정의된 'run' 타겟을 실행합니다.
run_%:
	@echo "🚀 Running in $(subst _,/,$(subst run_,,$@))..."
	$(MAKE) -C $(subst _,/,$(subst run_,,$@)) run