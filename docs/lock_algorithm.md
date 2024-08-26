
# ロックアルゴリズム
## 概念
**賢者**
開始前準備
おわったよ
開始する？
開始できた
始めるね？
始める

**マネージャー**
終わった？
開始前準備する
開始するよ
開始できた？
開始
はじめよっか

## 疑似コード
**賢者**
lock(done)
unlock(in_process)
lock(can_start)
unlock(can_start)
lock(fork1), lock(fork2)
lock(in_process)
unlock(done)
lock(done_manager)
unlock(done_manager)

**マネージャー**
lock(in_process)
lock(done_manager)
unlock(in_process)
unlock(can_start)
lock(done)
unlock(done)
lock(can_start)
unlock(done_manager)

## 抽象化後コード
**賢者**
start(setup_philo)
end(in_process)
wait(make_wait_philo)
lock(fork1), lock(fork2)
start(in_process)
end(setup_philo)
wait(setup_manager)

**マネージャー**
wait(in_process)
start(setup_manager)
end(make_wait_philo)
wait(setup_philo)
start(make_wait_philo)
end(setup_manager)
