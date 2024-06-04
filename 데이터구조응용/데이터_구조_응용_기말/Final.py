import cv2
import random
import numpy as np
import matplotlib.pyplot as plt
import pyautogui
from matplotlib.widgets import Button
import heapq

# 이미지 로드
imgList11 = ['num_1.png', 'num_2.png', 'num_3.png']
imgList12 = ['num_4.png', 'num_5.png', 'num_6.png']
imgList13 = ['num_7.png', 'num_8.png', 'num_0.png']
imgList1 = imgList11 + imgList12 + imgList13
imgList2 = random.sample(imgList1, 9)

# 이미지 로드 헬퍼 함수
def load_images(imgList):
    return [cv2.cvtColor(cv2.imread(img), cv2.COLOR_BGR2RGB) for img in imgList]

# 이미지 로드
images = load_images(imgList2)
img0 = cv2.cvtColor(cv2.imread('num_0.png'), cv2.COLOR_BGR2RGB)

# 이미지 표시
fig, axes = plt.subplots(3, 3, figsize=(5, 5))

for i, ax in enumerate(axes.flat):
    ax.imshow(images[i])
    ax.axis('off')

# 지정된 위치에 이미지를 업데이트
def update_image(pos, new_img):
    images[pos] = new_img
    ax = axes.flat[pos]
    ax.clear()
    ax.imshow(new_img)
    ax.axis('off')
    plt.draw()

# 지정된 위치의 이미지를 교체
def swap_images(pos1, pos2):
    images[pos1], images[pos2] = images[pos2], images[pos1]
    update_image(pos1, images[pos1])
    update_image(pos2, images[pos2])

# 현재 배치 상태가 성공인지 확인
def check_success():
    target_order = imgList11 + imgList12 + imgList13
    return imgList2 == target_order

# 휴리스틱 함수
def heuristic(state):
    target = imgList11 + imgList12 + imgList13
    return sum(s != t for s, t in zip(state, target))

# 가능한 이동을 반환하는 함수
def get_neighbors(state):
    neighbors = []
    zero_index = state.index('num_0.png')
    row, col = divmod(zero_index, 3)

    def swap_and_create(new_index):
        new_state = state[:]
        new_state[zero_index], new_state[new_index] = new_state[new_index], new_state[zero_index]
        neighbors.append(new_state)

    if row > 0: swap_and_create(zero_index - 3)
    if row < 2: swap_and_create(zero_index + 3)
    if col > 0: swap_and_create(zero_index - 1)
    if col < 2: swap_and_create(zero_index + 1)

    return neighbors

# A* 알고리즘
def astar(start, goal):
    frontier = [(heuristic(start), start)]
    heapq.heapify(frontier)
    came_from = {tuple(start): None}
    cost_so_far = {tuple(start): 0}

    while frontier:
        _, current = heapq.heappop(frontier)

        if current == goal:
            break

        for neighbor in get_neighbors(current):
            new_cost = cost_so_far[tuple(current)] + 1
            if tuple(neighbor) not in cost_so_far or new_cost < cost_so_far[tuple(neighbor)]:
                cost_so_far[tuple(neighbor)] = new_cost
                priority = new_cost + heuristic(neighbor)
                heapq.heappush(frontier, (priority, neighbor))
                came_from[tuple(neighbor)] = current

    # 경로를 재구성
    path = []
    current = goal
    while current != start:
        path.append(current)
        current = came_from[tuple(current)]
    path.reverse()
    return path

# 클릭 이벤트 핸들러
def add_point(event):
    if event.button == 1:
        fore = pyautogui.getActiveWindow()
        pos = pyautogui.position()
        x = pos.x - fore.left
        y = pos.y - fore.top
        print("클릭 : ", x, ", ", y)
        
        grid_x = (x - 75) // 130
        grid_y = (y - 95) // 130
        
        if 0 <= grid_x < 3 and 0 <= grid_y < 3:
            clicked_index = grid_y * 3 + grid_x
            if imgList2[clicked_index] != 'num_0.png':
                # 십자에서 0번사진 찾기
                adjacent_indices = []
                if grid_x > 0:
                    adjacent_indices.append(clicked_index - 1)
                if grid_x < 2:
                    adjacent_indices.append(clicked_index + 1)
                if grid_y > 0:
                    adjacent_indices.append(clicked_index - 3)
                if grid_y < 2:
                    adjacent_indices.append(clicked_index + 3)
                
                for adj_index in adjacent_indices:
                    if imgList2[adj_index] == 'num_0.png':
                        swap_images(clicked_index, adj_index)
                        imgList2[clicked_index], imgList2[adj_index] = imgList2[adj_index], imgList2[clicked_index]
                        
                        if check_success():
                            pyautogui.alert("축하합니다! 퍼즐을 완성했습니다.")
                        break

# Solve 버튼 클릭 핸들러
def solve_puzzle(event):
    if event.inaxes == button_ax1:
        goal = imgList11 + imgList12 + imgList13
        path = astar(imgList2, goal)
        for state in path:
            imgList2[:] = state
            images[:] = load_images(imgList2)
            for i, ax in enumerate(axes.flat):
                ax.clear()
                ax.imshow(images[i])
                ax.axis('off')
            plt.pause(0.1) #속도 조절은 이걸로하면 됌
        pyautogui.alert("퍼즐을 자동으로 풀었습니다!")

# Random 버튼 클릭 핸들러
def randomize_puzzle(event):
    if event.inaxes == button_ax2:
        global imgList2, images
        imgList2 = random.sample(imgList1, 9)
        images = load_images(imgList2)
        for i, ax in enumerate(axes.flat):
            ax.clear()
            ax.imshow(images[i])
            ax.axis('off')
        plt.draw()
        print("재시작")

# 첫 번째 버튼 (Solve)
button_ax1 = plt.axes([0.1, 0.02, 0.15, 0.05])
button1 = Button(button_ax1, 'Solve')

# 두 번째 버튼 (Random)
button_ax2 = plt.axes([0.8, 0.02, 0.15, 0.05])
button2 = Button(button_ax2, 'Random')

# 버튼 클릭 이벤트 핸들러 연결
button1.on_clicked(solve_puzzle)
button2.on_clicked(randomize_puzzle)

# 이벤트 연결
cid = plt.connect('button_press_event', add_point)
plt.subplots_adjust(wspace=0.01, hspace=0.02)
plt.show()
