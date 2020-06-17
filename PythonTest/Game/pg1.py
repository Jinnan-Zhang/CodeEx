import pygame
import sys

pygame.init()
v_x = int(sys.argv[1])
v_y = int(sys.argv[2])
size = width, height = 600, 400
speed = [v_x, v_y]
background = (255, 255, 255)
screen = pygame.display.set_mode(size)
pygame.display.set_caption("Here We Game!\n")

Faer = pygame.image.load("pics/Faer.jpg")
position = Faer.get_rect()

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
    position = position.move(speed)

    if position.left < 0 or position.right > width:
        Faer = pygame.transform.flip(Faer, True, False)
        speed[0] = -speed[0]
    if position.top < 0 or position.bottom > height:
        speed[1] = -speed[1]
    screen.fill(background)
    screen.blit(Faer, position)
    pygame.display.flip()
    pygame.time.delay(10)